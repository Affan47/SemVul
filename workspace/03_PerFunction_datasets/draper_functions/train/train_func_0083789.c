ScalableFont(gui::IGUIEnvironment *env, const io::path& filename)
	: Driver(0), SpriteBank(0), Environment(env), WrongCharacter(0),
		MaxHeight(0), GlobalKerningWidth(0), GlobalKerningHeight(0)
	{
	#ifdef _DEBUG
		setDebugName("ScalableFont");
	#endif

		m_fallback_font = NULL;
		m_fallback_kerning_width = 0;
		m_fallback_font_scale = 1.0f;
		m_scale = 0.37f;
		m_black_border = false;

		if (Environment)
		{

			Driver = Environment->getVideoDriver();

			SpriteBank = Environment->addEmptySpriteBank(filename);
			if (SpriteBank)
				SpriteBank->grab();
		}

		if (Driver)
			Driver->grab();

		setInvisibleCharacters ( L" " );

		io::IXMLReader* reader = env->getFileSystem()->createXMLReader(filename.c_str());
		if (reader)
		{
			load( reader );
			reader->drop();
		}
		assert_log(Areas.size() > 0);
	}
