clipToHyperPlane ( s4DVertex * dest, const s4DVertex * source, u32 inCount, const sVec4 &plane )
{
	u32 outCount = 0;
	s4DVertex * out = dest;

	const s4DVertex * a;
	const s4DVertex * b = source;

	f32 bDotPlane;

	bDotPlane = b->Pos.dotProduct ( plane );

	for( u32 i = 1; i < inCount + 1; ++i)
	{
		const s32 condition = i - inCount;
		const s32 index = (( ( condition >> 31 ) & ( i ^ condition ) ) ^ condition ) << 1;

		a = &source[ index ];


		if ( a->Pos.dotProduct ( plane ) <= 0.f )
		{

			if ( F32_GREATER_0 ( bDotPlane ) )
			{

				out->interpolate ( *b, *a, bDotPlane / (b->Pos - a->Pos).dotProduct ( plane ) );
				out += 2;
				outCount += 1;
			}


			irr::memcpy32_small ( out, a, SIZEOF_SVERTEX * 2 );
			b = out;

			out += 2;
			outCount += 1;
		}
		else
		{


			if ( F32_LOWER_EQUAL_0 (  bDotPlane ) )
			{


				out->interpolate ( *b, *a, bDotPlane / (b->Pos - a->Pos).dotProduct ( plane ) );
				out += 2;
				outCount += 1;
			}

			b = a;
		}

		bDotPlane = b->Pos.dotProduct ( plane );

	}

	return outCount;
}
