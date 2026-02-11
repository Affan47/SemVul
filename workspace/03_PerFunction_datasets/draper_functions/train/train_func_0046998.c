boxes_collection_filter_filter (BoxesCollectionFilter* self, BoxesCollectionItem* item) {
	gboolean result = FALSE;
	gchar* name = NULL;
	BoxesCollectionItem* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	gchar* _tmp3_ = NULL;
	gchar** _tmp4_ = NULL;
	gint _tmp4__length1 = 0;
#line 61 "/extra-data/checkout/gnome/gnome-boxes/src/collection.vala"
	g_return_val_if_fail (self != NULL, FALSE);
#line 61 "/extra-data/checkout/gnome/gnome-boxes/src/collection.vala"
	g_return_val_if_fail (item != NULL, FALSE);
#line 62 "/extra-data/checkout/gnome/gnome-boxes/src/collection.vala"
	_tmp0_ = item;
#line 62 "/extra-data/checkout/gnome/gnome-boxes/src/collection.vala"
	_tmp1_ = boxes_collection_item_get_name (_tmp0_);
#line 62 "/extra-data/checkout/gnome/gnome-boxes/src/collection.vala"
	_tmp2_ = _tmp1_;
#line 62 "/extra-data/checkout/gnome/gnome-boxes/src/collection.vala"
	_tmp3_ = boxes_canonicalize_for_search (_tmp2_);
#line 62 "/extra-data/checkout/gnome/gnome-boxes/src/collection.vala"
	name = _tmp3_;
#line 63 "/extra-data/checkout/gnome/gnome-boxes/src/collection.vala"
	_tmp4_ = self->priv->terms;
#line 63 "/extra-data/checkout/gnome/gnome-boxes/src/collection.vala"
	_tmp4__length1 = self->priv->terms_length1;
#line 655 "collection.c"
	{
		gchar** term_collection = NULL;
		gint term_collection_length1 = 0;
		gint _term_collection_size_ = 0;
		gint term_it = 0;
#line 63 "/extra-data/checkout/gnome/gnome-boxes/src/collection.vala"
		term_collection = _tmp4_;
#line 63 "/extra-data/checkout/gnome/gnome-boxes/src/collection.vala"
		term_collection_length1 = _tmp4__length1;
#line 63 "/extra-data/checkout/gnome/gnome-boxes/src/collection.vala"
		for (term_it = 0; term_it < _tmp4__length1; term_it = term_it + 1) {
#line 667 "collection.c"
			gchar* _tmp5_ = NULL;
			gchar* term = NULL;
#line 63 "/extra-data/checkout/gnome/gnome-boxes/src/collection.vala"
			_tmp5_ = g_strdup (term_collection[term_it]);
#line 63 "/extra-data/checkout/gnome/gnome-boxes/src/collection.vala"
			term = _tmp5_;
#line 674 "collection.c"
			{
				const gchar* _tmp6_ = NULL;
				const gchar* _tmp7_ = NULL;
				gboolean _tmp8_ = FALSE;
#line 64 "/extra-data/checkout/gnome/gnome-boxes/src/collection.vala"
				_tmp6_ = name;
#line 64 "/extra-data/checkout/gnome/gnome-boxes/src/collection.vala"
				_tmp7_ = term;
#line 64 "/extra-data/checkout/gnome/gnome-boxes/src/collection.vala"
				_tmp8_ = string_contains (_tmp6_, _tmp7_);
#line 64 "/extra-data/checkout/gnome/gnome-boxes/src/collection.vala"
				if (!_tmp8_) {
#line 65 "/extra-data/checkout/gnome/gnome-boxes/src/collection.vala"
					result = FALSE;
#line 65 "/extra-data/checkout/gnome/gnome-boxes/src/collection.vala"
					_g_free0 (term);
#line 65 "/extra-data/checkout/gnome/gnome-boxes/src/collection.vala"
					_g_free0 (name);
#line 65 "/extra-data/checkout/gnome/gnome-boxes/src/collection.vala"
					return result;
#line 695 "collection.c"
				}
#line 63 "/extra-data/checkout/gnome/gnome-boxes/src/collection.vala"
				_g_free0 (term);
#line 699 "collection.c"
			}
		}
	}
#line 67 "/extra-data/checkout/gnome/gnome-boxes/src/collection.vala"
	result = TRUE;
#line 67 "/extra-data/checkout/gnome/gnome-boxes/src/collection.vala"
	_g_free0 (name);
#line 67 "/extra-data/checkout/gnome/gnome-boxes/src/collection.vala"
	return result;
#line 709 "collection.c"
}
