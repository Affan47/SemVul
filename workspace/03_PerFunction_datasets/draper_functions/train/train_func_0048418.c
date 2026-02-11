transform_concatenatedColorTransform(const fn_call& fn)
{
    const double factor = 256.0;

    Transform_as* relay = ensure<ThisIsNative<Transform_as> >(fn);

    if (!fn.nargs) {


        as_value colorTrans(findObject(fn.env(), "flash.geom.ColorTransform"));

        as_function* colorTransformCtor = colorTrans.to_function();

        if (!colorTransformCtor) {
            IF_VERBOSE_ASCODING_ERRORS(
                log_aserror(_("Failed to construct flash.geom.ColorTransform!"));
            );
            return as_value();
        }


        const SWFCxForm& c = relay->worldColorTransform();

        fn_call::Args args;
        args += c.ra / factor, c.ga / factor, c.ba / factor, c.aa / factor,
             c.rb, c.gb, c.bb, c.ab;

        as_object* colorTransformObj =
            constructInstance(*colorTransformCtor, fn.env(), args);

        return as_value(colorTransformObj);
    }

    return as_value();
}
