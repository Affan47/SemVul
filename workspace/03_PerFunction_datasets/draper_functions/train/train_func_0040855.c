pop(VMSTATE vms) {
  if (vms->c.vm_top <= 0){
    vms->c.vm_top = 1;
    vms->c.vm_state = VM_STATE_DYING;
  }

  vms->c.vm_top--;
  return AT(vms->r->vm_stack, vms->c.vm_top);
}
