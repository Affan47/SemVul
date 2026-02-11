conn_resume_readline(VECTOR args) {
  int retval = conn_gets((BVECTOR) AT(args, 0),
			 NUM(AT(args, 1)),
			 NUM(AT(args, 2)),
			 (OVECTOR) AT(args, 3));

  switch (retval) {
    case CONN_RET_BLOCK:
      break;

    case CONN_RET_ERROR:
      unblock_thread(current_thread);
      current_thread->vms->r->vm_acc = false;
      break;

    default:
      unblock_thread(current_thread);
      current_thread->vms->r->vm_acc = (OBJ) newstring((char *) ((BVECTOR) AT(args, 0))->vec);
      break;
  }

  return retval;
}
