bitwise_filter_destroy(Slapi_PBlock* pb)
{
    void *obj = NULL;
    slapi_pblock_get(pb, SLAPI_PLUGIN_OBJECT, &obj);
    if (obj) {
	struct bitwise_match_cb *bmc = (struct bitwise_match_cb *)obj;
	delete_bitwise_match_cb(bmc);
	obj = NULL;
	slapi_pblock_set(pb, SLAPI_PLUGIN_OBJECT, obj);
    }
}
