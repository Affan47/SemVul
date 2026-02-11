ReadAsciiFile(Scene& out, StreamReaderLE* stream)
{
	ChunkInfo ci;
	for(LineSplitter splitter(*stream);splitter;++splitter) {


		if (splitter.match_start("PolH ")) {
			ReadChunkInfo_Ascii(ci,splitter);
			ReadPolH_Ascii(out,splitter,ci);
		}
		if (splitter.match_start("BitM ")) {
			ReadChunkInfo_Ascii(ci,splitter);
			ReadBitM_Ascii(out,splitter,ci);
		}
		if (splitter.match_start("Mat1 ")) {
			ReadChunkInfo_Ascii(ci,splitter);
			ReadMat1_Ascii(out,splitter,ci);
		}
		if (splitter.match_start("Grou ")) {
			ReadChunkInfo_Ascii(ci,splitter);
			ReadGrou_Ascii(out,splitter,ci);
		}
		if (splitter.match_start("Lght ")) {
			ReadChunkInfo_Ascii(ci,splitter);
			ReadLght_Ascii(out,splitter,ci);
		}
		if (splitter.match_start("Came ")) {
			ReadChunkInfo_Ascii(ci,splitter);
			ReadCame_Ascii(out,splitter,ci);
		}
		if (splitter.match_start("Bone ")) {
			ReadChunkInfo_Ascii(ci,splitter);
			ReadBone_Ascii(out,splitter,ci);
		}
		if (splitter.match_start("Chan ")) {
			ReadChunkInfo_Ascii(ci,splitter);
			ReadChan_Ascii(out,splitter,ci);
		}
		if (splitter.match_start("Unit ")) {
			ReadChunkInfo_Ascii(ci,splitter);
			ReadUnit_Ascii(out,splitter,ci);
		}
		if (splitter.match_start("END ")) {


			return;
		}
	}
}
