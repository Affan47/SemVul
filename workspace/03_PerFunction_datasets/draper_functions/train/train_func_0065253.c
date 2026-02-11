socketClientPushReceiveData(JsVar *connection, JsVar *socket, JsVar **receiveData) {
  if (*receiveData) {
    if (jsvGetStringLength(*receiveData)==0 ||
        jswrap_stream_pushData(socket, *receiveData, false)) {

      jsvObjectSetChild(connection,HTTP_NAME_RECEIVE_DATA,0);
      jsvUnLock(*receiveData);
      *receiveData = 0;
    }
  }
}
