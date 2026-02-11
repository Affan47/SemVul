readObjectChunk(io::IReadFile* file, ChunkData* parent)
{
#ifdef _IRR_DEBUG_3DS_LOADER_
	os::Printer::log("Load object chunk.");
#endif
	while(parent->read < parent->header.length)
	{
		ChunkData data;
		readChunkData(file, data);

		switch(data.header.id)
		{
		case C3DS_OBJTRIMESH:
			readObjectChunk(file, &data);
			break;

		case C3DS_TRIVERT:
			readVertices(file, data);
			break;

		case C3DS_POINTFLAGARRAY:
			{
				u16 numVertex, flags;
				file->read(&numVertex, sizeof(u16));
#ifdef __BIG_ENDIAN__
				numVertex= os::Byteswap::byteswap(numVertex);
#endif
				for (u16 i=0; i<numVertex; ++i)
				{
					file->read(&flags, sizeof(u16));
#ifdef __BIG_ENDIAN__
					flags = os::Byteswap::byteswap(flags);
#endif
				}
				data.read += (numVertex+1)*sizeof(u16);
			}
			break;

		case C3DS_TRIFACE:
			readIndices(file, data);
			readObjectChunk(file, &data);
			break;

		case C3DS_TRIFACEMAT:
			readMaterialGroup(file, data);
			break;

		case C3DS_TRIUV:
			readTextureCoords(file, data);
			break;

		case C3DS_TRIMATRIX:
			{
				f32 mat[4][3];
				file->read(&mat, 12*sizeof(f32));
				TransformationMatrix.makeIdentity();
				for (int i=0; i<4; ++i)
				{
					for (int j=0; j<3; ++j)
					{
#ifdef __BIG_ENDIAN__
						TransformationMatrix(i,j)=os::Byteswap::byteswap(mat[i][j]);
#else
						TransformationMatrix(i,j)=mat[i][j];
#endif
					}
				}
				data.read += 12*sizeof(f32);
			}
			break;
		case C3DS_MESHCOLOR:
			{
				u8 flag;
				file->read(&flag, sizeof(u8));
				++data.read;
			}
			break;
		case C3DS_TRISMOOTH:
			{
				SmoothingGroups = new u32[CountFaces];
				file->read(SmoothingGroups, CountFaces*sizeof(u32));
#ifdef __BIG_ENDIAN__
				for (u16 i=0; i<CountFaces; ++i)
					SmoothingGroups[i] = os::Byteswap::byteswap(SmoothingGroups[i]);
#endif
				data.read += CountFaces*sizeof(u32);
			}
			break;

		default:

			file->seek(data.header.length - data.read, true);
			data.read += data.header.length - data.read;
		}

		parent->read += data.read;
	}

	return true;
}
