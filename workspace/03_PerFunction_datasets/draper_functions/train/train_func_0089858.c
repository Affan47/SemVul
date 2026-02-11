sys_q_remove_calltf(PLI_BYTE8 *name)
{
      vpiHandle callh = vpi_handle(vpiSysTfCall, 0);
      vpiHandle argv = vpi_iterate(vpiArgument, callh);
      vpiHandle job, inform, status;
      PLI_INT32 id, idx;
      s_vpi_vecval job_val, inform_val;
      s_vpi_value val;
      unsigned invalid_id;


      invalid_id = get_valid_32(vpi_scan(argv), &id);


      job = vpi_scan(argv);


      inform = vpi_scan(argv);


      status = vpi_scan(argv);


      vpi_free_object(argv);


      idx = get_id_index(id);
      if (invalid_id || (idx < 0)) {
	    fill_variable_with_x(job);
	    fill_variable_with_x(inform);
	    val.format = vpiIntVal;
	    val.value.integer = IVL_QUEUE_UNDEFINED_ID;
	    vpi_put_value(status, &val, 0, vpiNoDelay);
	    return 0;
      }


      if (remove_from_queue(idx, &job_val, &inform_val)) {
	    fill_variable_with_x(job);
	    fill_variable_with_x(inform);
	    val.format = vpiIntVal;
	    val.value.integer = IVL_QUEUE_EMPTY;
	    vpi_put_value(status, &val, 0, vpiNoDelay);
	    return 0;
      }

      val.format = vpiVectorVal;
      val.value.vector = &job_val;
      vpi_put_value(job, &val, 0, vpiNoDelay);
      val.format = vpiVectorVal;
      val.value.vector = &inform_val;
      vpi_put_value(inform, &val, 0, vpiNoDelay);


      val.format = vpiIntVal;
      val.value.integer = IVL_QUEUE_OK;
      vpi_put_value(status, &val, 0, vpiNoDelay);
      return 0;
}
