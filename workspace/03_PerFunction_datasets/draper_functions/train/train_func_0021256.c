K_release_message_envelope(MessageEnvelope* env) {
  strcpy(env->data, "");
  mq_remove(env, current_process->message_send);
  mq_remove(env, current_process->message_receive);
  mq_enqueue(env, _feq);
  if (!ppq_is_empty(_ewq)) {
    PCB* nextPCB = ppq_dequeue(_ewq);
    nextPCB->state = READY;
    ppq_enqueue(nextPCB, _rpq);
  }
}
