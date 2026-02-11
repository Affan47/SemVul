ipath_create_rcvhdrq(struct ipath_devdata *dd,
			 struct ipath_portdata *pd)
{
	int ret = 0;

	if (!pd->port_rcvhdrq) {
		dma_addr_t phys_hdrqtail;
		gfp_t gfp_flags = GFP_USER | __GFP_COMP;
		int amt = ALIGN(dd->ipath_rcvhdrcnt * dd->ipath_rcvhdrentsize *
				sizeof(u32), PAGE_SIZE);

		pd->port_rcvhdrq = dma_alloc_coherent(
			&dd->pcidev->dev, amt, &pd->port_rcvhdrq_phys,
			gfp_flags);

		if (!pd->port_rcvhdrq) {
			ipath_dev_err(dd, "attempt to allocate %d bytes "
				      "for port %u rcvhdrq failed\n",
				      amt, pd->port_port);
			ret = -ENOMEM;
			goto bail;
		}

		if (!(dd->ipath_flags & IPATH_NODMA_RTAIL)) {
			pd->port_rcvhdrtail_kvaddr = dma_alloc_coherent(
				&dd->pcidev->dev, PAGE_SIZE, &phys_hdrqtail,
				GFP_KERNEL);
			if (!pd->port_rcvhdrtail_kvaddr) {
				ipath_dev_err(dd, "attempt to allocate 1 page "
					"for port %u rcvhdrqtailaddr "
					"failed\n", pd->port_port);
				ret = -ENOMEM;
				dma_free_coherent(&dd->pcidev->dev, amt,
					pd->port_rcvhdrq,
					pd->port_rcvhdrq_phys);
				pd->port_rcvhdrq = NULL;
				goto bail;
			}
			pd->port_rcvhdrqtailaddr_phys = phys_hdrqtail;
			ipath_cdbg(VERBOSE, "port %d hdrtailaddr, %llx "
				   "physical\n", pd->port_port,
				   (unsigned long long) phys_hdrqtail);
		}

		pd->port_rcvhdrq_size = amt;

		ipath_cdbg(VERBOSE, "%d pages at %p (phys %lx) size=%lu "
			   "for port %u rcvhdr Q\n",
			   amt >> PAGE_SHIFT, pd->port_rcvhdrq,
			   (unsigned long) pd->port_rcvhdrq_phys,
			   (unsigned long) pd->port_rcvhdrq_size,
			   pd->port_port);
	} else {
		ipath_cdbg(VERBOSE, "reuse port %d rcvhdrq @%p %llx phys; "
			   "hdrtailaddr@%p %llx physical\n",
			   pd->port_port, pd->port_rcvhdrq,
			   (unsigned long long) pd->port_rcvhdrq_phys,
			   pd->port_rcvhdrtail_kvaddr, (unsigned long long)
			   pd->port_rcvhdrqtailaddr_phys);
	}

	memset(pd->port_rcvhdrq, 0, pd->port_rcvhdrq_size);
	if (pd->port_rcvhdrtail_kvaddr)
		memset(pd->port_rcvhdrtail_kvaddr, 0, PAGE_SIZE);


	ipath_write_kreg_port(dd, dd->ipath_kregs->kr_rcvhdrtailaddr,
			      pd->port_port, pd->port_rcvhdrqtailaddr_phys);
	ipath_write_kreg_port(dd, dd->ipath_kregs->kr_rcvhdraddr,
			      pd->port_port, pd->port_rcvhdrq_phys);

bail:
	return ret;
}
