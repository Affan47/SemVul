networkGetFromVar(JsNetwork *net) {
  net->networkVar = jsvObjectGetChild(execInfo.hiddenRoot, NETWORK_VAR_NAME, 0);
  if (!net->networkVar) {
#ifdef LINUX
    networkCreate(net, JSNETWORKTYPE_SOCKET);
    return net->networkVar != 0;
#else
    return false;
#endif
  }
  jsvGetString(net->networkVar, (char *)&net->data, sizeof(JsNetworkData)+1);

  switch (net->data.type) {
#if defined(USE_CC3000)
  case JSNETWORKTYPE_CC3000 : netSetCallbacks_cc3000(net); break;
#endif
#if defined(USE_WIZNET)
  case JSNETWORKTYPE_W5500 : netSetCallbacks_wiznet(net); break;
#endif
#if defined(USE_ESP8266)
  case JSNETWORKTYPE_ESP8266 : netSetCallbacks_esp8266(net); break;
#endif
#if defined(LINUX)
  case JSNETWORKTYPE_SOCKET : netSetCallbacks_linux(net); break;
#endif
  case JSNETWORKTYPE_JS : netSetCallbacks_js(net); break;
  default:
    jsError("Unknown network device %d", net->data.type);
    networkFree(net);
    return false;
  }
  networkCurrentStruct = net;
  return true;
}
