ConvertTransformOperator(IfcMatrix4& out, const IfcCartesianTransformationOperator& op)
{
	IfcVector3 loc;
	ConvertCartesianPoint(loc,op.LocalOrigin);

	IfcVector3 x(1.f,0.f,0.f),y(0.f,1.f,0.f),z(0.f,0.f,1.f);
	if (op.Axis1) {
		ConvertDirection(x,*op.Axis1.Get());
	}
	if (op.Axis2) {
		ConvertDirection(y,*op.Axis2.Get());
	}
	if (const IfcCartesianTransformationOperator3D* op2 = op.ToPtr<IfcCartesianTransformationOperator3D>()) {
		if(op2->Axis3) {
			ConvertDirection(z,*op2->Axis3.Get());
		}
	}

	IfcMatrix4 locm;
	IfcMatrix4::Translation(loc,locm);
	AssignMatrixAxes(out,x,y,z);


	IfcVector3 vscale;
	if (const IfcCartesianTransformationOperator3DnonUniform* nuni = op.ToPtr<IfcCartesianTransformationOperator3DnonUniform>()) {
		vscale.x = nuni->Scale?op.Scale.Get():1.f;
		vscale.y = nuni->Scale2?nuni->Scale2.Get():1.f;
		vscale.z = nuni->Scale3?nuni->Scale3.Get():1.f;
	}
	else {
		const IfcFloat sc = op.Scale?op.Scale.Get():1.f;
		vscale = IfcVector3(sc,sc,sc);
	}

	IfcMatrix4 s;
	IfcMatrix4::Scaling(vscale,s);

	out = locm * out * s;
}
