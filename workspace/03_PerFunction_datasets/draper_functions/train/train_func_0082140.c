alloc_dummy_hdrq(struct qib_devdata *dd)
{
	dd->cspec->dummy_hdrq = dma_alloc_coherent(&dd->pcidev->dev,
					dd->rcd[0]->rcvhdrq_size,
					&dd->cspec->dummy_hdrq_phys,
					GFP_ATOMIC | __GFP_COMP);
	if (!dd->cspec->dummy_hdrq) {
		qib_devinfo(dd->pcidev, "Couldn't allocate dummy hdrq\n");

		dd->cspec->dummy_hdrq_phys = 0UL;
	}
}
