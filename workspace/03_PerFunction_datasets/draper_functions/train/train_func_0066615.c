ossl_ec_point_to_bn(VALUE self)
{
    EC_POINT *point;
    VALUE bn_obj;
    VALUE group_v = rb_iv_get(self, "@group");
    const EC_GROUP *group;
    point_conversion_form_t form;
    BIGNUM *bn;

    Require_EC_POINT(self, point);
    SafeRequire_EC_GROUP(group_v, group);

    form = EC_GROUP_get_point_conversion_form(group);

    bn_obj = rb_obj_alloc(cBN);
    bn = GetBNPtr(bn_obj);

    if (EC_POINT_point2bn(group, point, form, bn, ossl_bn_ctx) == NULL)
        ossl_raise(eEC_POINT, "EC_POINT_point2bn");

    return bn_obj;
}
