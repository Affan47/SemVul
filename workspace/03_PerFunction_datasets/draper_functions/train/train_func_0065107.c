sensorsNetworkStop(){

  FAIL(pthread_cancel(pthreadSensorsRec));
  FAIL(pthread_cancel(pthreadSensorsSend));
  FAIL(close(sock));
  FAIL(mq_close(mqSensorsSend));
  puts("Closed");
}
