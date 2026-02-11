main(int argc, char *argv[])
{
    char *input, *output;
    int convertNull;
    double nullValue;
    int useTypeDefault, type, useLzwDefault, doLzw, useRleDefault, doRle;
    int usePrecisionDefault, precision, useDimensionDefault, tileX, tileY,
	tileZ;
    G3D_Region region;
    struct GModule *module;

    map = NULL;

    G_gisinit(argv[0]);
    module = G_define_module();
    module->keywords = _("raster3d, voxel, import");
    module->description =
	_("Imports 3-dimensional Vis5D files (i.e. the V5D file with 1 variable and 1 time step).");

    setParams();
    G3d_setStandard3dInputParams();

    if (G_parser(argc, argv))
	exit(1);

    getParams(&input, &output, &convertNull, &nullValue);
    if (!G3d_getStandard3dParams(&useTypeDefault, &type,
				 &useLzwDefault, &doLzw,
				 &useRleDefault, &doRle,
				 &usePrecisionDefault, &precision,
				 &useDimensionDefault, &tileX, &tileY,
				 &tileZ))
	fatalError("main: error getting standard parameters");

    G3d_getWindow(&region);
    map = G3d_openCellNew(output, FCELL_TYPE, G3D_USE_CACHE_XY, &region);
    if (map == NULL)
	fatalError(_("Unable to open 3D raster map"));

    convert(input, &region, convertNull, nullValue);

    if (!G3d_closeCell(map))
	fatalError(_("Unable to close 3D raster map"));
    map = NULL;

    return 0;
}
