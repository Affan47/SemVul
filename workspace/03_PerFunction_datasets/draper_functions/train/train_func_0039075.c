AddArray(xmlNode* parent, const char* id, const FMVector4List& values)
	{

		FUSStringBuilder builder;
		size_t valueCount = values.size();
		builder.reserve(valueCount * 4 * FLOAT_STR_ESTIMATE);
		if (valueCount > 0)
		{

			FMVector4List::const_iterator itP = values.begin();
			FUStringConversion::ToString(builder, *itP);
			for (++itP; itP != values.end(); ++itP) { builder.append(' '); FUStringConversion::ToString(builder, *itP); }
		}


		return AddArray(parent, id, DAE_FLOAT_ARRAY_ELEMENT, builder.ToCharPtr(), valueCount * 4);
	}
