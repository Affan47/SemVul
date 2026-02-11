tp_protocol_list_features (TpProxyClass *cls G_GNUC_UNUSED)
{
  static TpProxyFeature features[N_FEAT + 1] = { { 0 } };

  if (G_LIKELY (features[0].name != 0))
    return features;


  features[FEAT_PARAMETERS].name = TP_PROTOCOL_FEATURE_PARAMETERS;
  features[FEAT_PARAMETERS].core = TRUE;
  features[FEAT_CORE].name = TP_PROTOCOL_FEATURE_CORE;
  features[FEAT_CORE].core = TRUE;


  g_assert (features[N_FEAT].name == 0);

  return features;
}
