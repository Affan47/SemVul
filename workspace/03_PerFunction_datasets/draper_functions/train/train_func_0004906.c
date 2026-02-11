max98088_handle_eq_pdata(struct snd_soc_codec *codec)
{
       struct max98088_priv *max98088 = snd_soc_codec_get_drvdata(codec);
       struct max98088_pdata *pdata = max98088->pdata;
       struct max98088_eq_cfg *cfg;
       unsigned int cfgcnt;
       int i, j;
       const char **t;
       int ret;
       struct snd_kcontrol_new controls[] = {
               SOC_ENUM_EXT((char *)eq_mode_name[0],
                       max98088->eq_enum,
                       max98088_get_eq_enum,
                       max98088_put_eq_enum),
               SOC_ENUM_EXT((char *)eq_mode_name[1],
                       max98088->eq_enum,
                       max98088_get_eq_enum,
                       max98088_put_eq_enum),
       };
       BUILD_BUG_ON(ARRAY_SIZE(controls) != ARRAY_SIZE(eq_mode_name));

       cfg = pdata->eq_cfg;
       cfgcnt = pdata->eq_cfgcnt;


       max98088->eq_textcnt = 0;
       max98088->eq_texts = NULL;
       for (i = 0; i < cfgcnt; i++) {
               for (j = 0; j < max98088->eq_textcnt; j++) {
                       if (strcmp(cfg[i].name, max98088->eq_texts[j]) == 0)
                               break;
               }

               if (j != max98088->eq_textcnt)
                       continue;


               t = krealloc(max98088->eq_texts,
                            sizeof(char *) * (max98088->eq_textcnt + 1),
                            GFP_KERNEL);
               if (t == NULL)
                       continue;


               t[max98088->eq_textcnt] = cfg[i].name;
               max98088->eq_textcnt++;
               max98088->eq_texts = t;
       }


       max98088->eq_enum.texts = max98088->eq_texts;
       max98088->eq_enum.items = max98088->eq_textcnt;

       ret = snd_soc_add_codec_controls(codec, controls, ARRAY_SIZE(controls));
       if (ret != 0)
               dev_err(codec->dev, "Failed to add EQ control: %d\n", ret);
}
