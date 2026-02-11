sbasic_cpriv_free(snd_mixer_class_t *class)
{
	struct bclass_private *priv = snd_mixer_sbasic_get_private(class);
	struct bclass_selector *sel;
	struct bclass_sid *sid;
	struct list_head *pos, *pos1;

	list_for_each_safe(pos, pos1, &priv->selectors) {
		sel = list_entry(pos, struct bclass_selector, list);
		free(sel);
	}
	list_for_each_safe(pos, pos1, &priv->sids) {
		sid = list_entry(pos, struct bclass_sid, list);
		free(sid);
	}
	free(priv);
}
