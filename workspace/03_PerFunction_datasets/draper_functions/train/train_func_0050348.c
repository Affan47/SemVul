init_fonts_list()
{
    if (!list_fonts_init)
    {
		list_registered_fonts.clear();


#if 0
	#define SAVE_COMPRESSED( ARR )    	\
			{ \
				list_registered_fonts[#ARR].resize(sizeof(mrpt_font_##ARR));  \
				memcpy(&list_registered_fonts[#ARR][0], mrpt_font_##ARR, sizeof(mrpt_font_##ARR)); \
				cout << #ARR << " -> " <<  sizeof(mrpt_font_##ARR) << endl;  \
				CFileGZOutputStream f(string("mrpt_font_")+string(#ARR)+string(".gz")); \
				f.WriteBuffer(mrpt_font_##ARR, sizeof(mrpt_font_##ARR)); \
				  \
			}

    	SAVE_COMPRESSED(5x7)


	#if MRPT_HAS_ASIAN_FONTS

	#endif

#endif

#if 1

		#define LOAD_FONT(FONTNAME) \
		{ \
			vector_byte tmpBuf(sizeof(mrpt_font_gz_##FONTNAME)); \
			memcpy(&tmpBuf[0], mrpt_font_gz_##FONTNAME, sizeof(mrpt_font_gz_##FONTNAME)); \
			mrpt::compress::zip::decompress_gz_data_block(tmpBuf,list_registered_fonts[#FONTNAME]); \
		}

		LOAD_FONT(5x7)
		LOAD_FONT(6x13)
		LOAD_FONT(6x13B)
		LOAD_FONT(6x13O)
		LOAD_FONT(9x15)
		LOAD_FONT(9x15B)
		LOAD_FONT(10x20)
#if MRPT_HAS_ASIAN_FONTS
		LOAD_FONT(18x18ja)
#endif

#endif

        list_fonts_init=true;
    }
}
