pathSegListFromSVGData(SVGPathSegList* path , const String& d, bool process)
{
    SVGPathSegListBuilder builder;
    return builder.build(path, d, process);
}
