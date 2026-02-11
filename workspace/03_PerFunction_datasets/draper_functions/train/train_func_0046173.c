networkCreate(JsNetwork *net, JsNetworkType type) {
  net->networkVar = jsvNewStringOfLength(sizeof(JsNetworkData));
  if (!net->networkVar) return;
  net->data.type = type;
  net->data.device = EV_NONE;
  net->data.pinCS = PIN_UNDEFINED;
  net->data.pinIRQ = PIN_UNDEFINED;
  net->data.pinEN = PIN_UNDEFINED;
  jsvUnLock(jsvObjectSetChild(execInfo.hiddenRoot, NETWORK_VAR_NAME, net->networkVar));
  networkSet(net);
  networkGetFromVar(net);
}
