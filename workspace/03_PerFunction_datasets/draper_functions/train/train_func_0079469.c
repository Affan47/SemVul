setDefault ()
{
	debugState = EDS_OFF;
	gravityState = 1;
	flyTroughState = 0;
	wireFrame = 0;
	guiActive = 1;
	guiInputActive = 0;
	GammaValue = 1.f;


#if defined ( _IRR_WINDOWS_ )
	deviceParam.DriverType = EDT_DIRECT3D9;
#else
	deviceParam.DriverType = EDT_OPENGL;
#endif
	deviceParam.WindowSize.Width = 800;
	deviceParam.WindowSize.Height = 600;
	deviceParam.Fullscreen = false;
	deviceParam.Bits = 24;
	deviceParam.ZBufferBits = 16;
	deviceParam.Vsync = false;
	deviceParam.AntiAlias = false;


	loadParam.defaultLightMapMaterial = EMT_LIGHTMAP;
	loadParam.defaultModulate = EMFN_MODULATE_1X;
	loadParam.defaultFilter = EMF_ANISOTROPIC_FILTER;
	loadParam.verbose = 2;
	loadParam.mergeShaderBuffer = 1;
	loadParam.cleanUnResolvedMeshes = 1;
	loadParam.loadAllShaders = 1;
	loadParam.loadSkyShader = 0;
	loadParam.alpharef = 1;

	sound = 0;

	CurrentMapName = "";
	CurrentArchiveList.clear ();


	CurrentArchiveList.push_back ( StartupDir + "../../media/" );


	CurrentArchiveList.push_back("/q/baseq3/");

	CurrentArchiveList.push_back(StartupDir + "../../media/map-20kdm2.pk3");
}
