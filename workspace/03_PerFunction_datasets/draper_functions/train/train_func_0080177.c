smp_request_await_tc_event(struct isci_request *ireq,
			   u32 completion_code)
{
	switch (SCU_GET_COMPLETION_TL_STATUS(completion_code)) {
	case SCU_MAKE_COMPLETION_STATUS(SCU_TASK_DONE_GOOD):
		ireq->scu_status = SCU_TASK_DONE_GOOD;
		ireq->sci_status = SCI_SUCCESS;
		sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
		break;
	default:


		ireq->scu_status = SCU_NORMALIZE_COMPLETION_STATUS(completion_code);
		ireq->sci_status = SCI_FAILURE_CONTROLLER_SPECIFIC_IO_ERR;
		sci_change_state(&ireq->sm, SCI_REQ_COMPLETED);
		break;
	}

	return SCI_SUCCESS;
}
