InvokeDefault (const NPVariant *argv,
                              uint32_t argc,
                              NPVariant *_result)
{
  if (!IsValid ())
    return false;

  NOTE (g_print ("totemNPObject::InvokeDefault [%p]\n", (void*) this));
  int defaultMethodIndex = GetClass()->GetDefaultMethodIndex ();
  if (defaultMethodIndex >= 0)
    return InvokeByIndex (defaultMethodIndex, argv, argc, _result);

  return false;
}
