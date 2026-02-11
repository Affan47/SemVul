max98088_handle_pdata(struct snd_soc_codec *codec)
{
       struct max98088_priv *max98088 = snd_soc_codec_get_drvdata(codec);
       struct max98088_pdata *pdata = max98088->pdata;
       u8 regval = 0;

       if (!pdata) {
               dev_dbg(codec->dev, "No platform data\n");
               return;
       }


       if (pdata->digmic_left_mode)
               regval |= M98088_DIGMIC_L;

       if (pdata->digmic_right_mode)
               regval |= M98088_DIGMIC_R;

       max98088->digmic = (regval ? 1 : 0);

       snd_soc_write(codec, M98088_REG_48_CFG_MIC, regval);


       regval = ((pdata->receiver_mode) ? M98088_REC_LINEMODE : 0);
       snd_soc_update_bits(codec, M98088_REG_2A_MIC_REC_CNTL,
               M98088_REC_LINEMODE_MASK, regval);


       if (pdata->eq_cfgcnt)
               max98088_handle_eq_pdata(codec);
}
