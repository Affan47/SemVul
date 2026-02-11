getAs3DObject( mrpt::opengl::CSetOfObjectsPtr	&outObj ) const
{
	if (!genericMapParams.enableSaveAs3DObject) return;


	mrpt::opengl::CSetOfObjectsPtr other_obj = mrpt::opengl::CSetOfObjects::Create();
	getAs3DObject(outObj, other_obj);
}
