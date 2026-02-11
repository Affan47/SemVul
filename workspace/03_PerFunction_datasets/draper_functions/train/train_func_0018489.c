trust_model_string(void)
{
  switch(opt.trust_model)
    {
    case TM_CLASSIC:  return "classic";
    case TM_PGP:      return "PGP";
    case TM_EXTERNAL: return "external";
    case TM_ALWAYS:   return "always";
    case TM_DIRECT:   return "direct";
    default:          return "unknown";
    }
}
