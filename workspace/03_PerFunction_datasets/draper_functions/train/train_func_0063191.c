_tp_account_list_features (TpProxyClass *cls G_GNUC_UNUSED)
{
  static TpProxyFeature features[N_FEAT + 1] = { { 0 } };

  if (G_UNLIKELY (features[0].name == 0))
    {
      features[FEAT_CORE].name = TP_ACCOUNT_FEATURE_CORE;
      features[FEAT_CORE].core = TRUE;


      features[FEAT_CONNECTION].name = TP_ACCOUNT_FEATURE_CONNECTION;
      features[FEAT_CONNECTION].prepare_async =
        tp_account_prepare_connection_async;

      features[FEAT_ADDRESSING].name = TP_ACCOUNT_FEATURE_ADDRESSING;
      features[FEAT_ADDRESSING].prepare_async =
        tp_account_prepare_addressing_async;

      features[FEAT_STORAGE].name = TP_ACCOUNT_FEATURE_STORAGE;
      features[FEAT_STORAGE].prepare_async =
        tp_account_prepare_storage_async;


      g_assert (features[N_FEAT].name == 0);
    }

  return features;
}
