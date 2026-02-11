_base_build_sg_ieee(struct MPT3SAS_ADAPTER *ioc, void *psge,
	dma_addr_t data_out_dma, size_t data_out_sz, dma_addr_t data_in_dma,
	size_t data_in_sz)
{
	u8 sgl_flags;

	if (!data_out_sz && !data_in_sz) {
		_base_build_zero_len_sge_ieee(ioc, psge);
		return;
	}

	if (data_out_sz && data_in_sz) {

		sgl_flags = MPI2_IEEE_SGE_FLAGS_SIMPLE_ELEMENT |
		    MPI2_IEEE_SGE_FLAGS_SYSTEM_ADDR;
		_base_add_sg_single_ieee(psge, sgl_flags, 0, data_out_sz,
		    data_out_dma);


		psge += ioc->sge_size_ieee;


		sgl_flags |= MPI25_IEEE_SGE_FLAGS_END_OF_LIST;
		_base_add_sg_single_ieee(psge, sgl_flags, 0, data_in_sz,
		    data_in_dma);
	} else if (data_out_sz)  {
		sgl_flags = MPI2_IEEE_SGE_FLAGS_SIMPLE_ELEMENT |
		    MPI25_IEEE_SGE_FLAGS_END_OF_LIST |
		    MPI2_IEEE_SGE_FLAGS_SYSTEM_ADDR;
		_base_add_sg_single_ieee(psge, sgl_flags, 0, data_out_sz,
		    data_out_dma);
	} else if (data_in_sz)  {
		sgl_flags = MPI2_IEEE_SGE_FLAGS_SIMPLE_ELEMENT |
		    MPI25_IEEE_SGE_FLAGS_END_OF_LIST |
		    MPI2_IEEE_SGE_FLAGS_SYSTEM_ADDR;
		_base_add_sg_single_ieee(psge, sgl_flags, 0, data_in_sz,
		    data_in_dma);
	}
}
