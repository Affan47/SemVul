get_flash_filters_package(const fn_call& fn)
{

    log_debug("Loading flash.filters package");
    Global_as& gl = getGlobal(fn);
    as_object* pkg = createObject(gl);

    VM& vm = getVM(fn);

    bitmapfilter_class_init(*pkg, getURI(vm, "BitmapFilter"));
    bevelfilter_class_init(*pkg, getURI(vm, "BevelFilter"));
    blurfilter_class_init(*pkg, getURI(vm, "BlurFilter"));
    colormatrixfilter_class_init(*pkg, getURI(vm, "ColorMatrixFilter"));
    convolutionfilter_class_init(*pkg, getURI(vm, "ConvolutionFilter"));
    displacementmapfilter_class_init(*pkg, getURI(vm, "DisplacementMapFilter"));
    dropshadowfilter_class_init(*pkg, getURI(vm, "DropShadowFilter"));
    glowfilter_class_init(*pkg, getURI(vm, "GlowFilter"));
    gradientbevelfilter_class_init(*pkg, getURI(vm, "GradientBevelFilter"));
    gradientglowfilter_class_init(*pkg, getURI(vm, "GradientGlowFilter"));

    return pkg;
}
