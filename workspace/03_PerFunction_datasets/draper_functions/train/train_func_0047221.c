ConvertColor(aiColor4D& out, const IfcColourOrFactor& in,ConversionData& conv,const aiColor4D* base)
{
	if (const EXPRESS::REAL* const r = in.ToPtr<EXPRESS::REAL>()) {
		out.r = out.g = out.b = static_cast<float>(*r);
		if(base) {
			out.r *= static_cast<float>( base->r );
			out.g *= static_cast<float>( base->g );
			out.b *= static_cast<float>( base->b );
			out.a = static_cast<float>( base->a );
		}
		else out.a = 1.0;
	}
	else if (const IfcColourRgb* const rgb = in.ResolveSelectPtr<IfcColourRgb>(conv.db)) {
		ConvertColor(out,*rgb);
	}
	else {
		IFCImporter::LogWarn("skipping unknown IfcColourOrFactor entity");
	}
}
