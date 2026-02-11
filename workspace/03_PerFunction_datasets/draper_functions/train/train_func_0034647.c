processSourceSentence(const char * sourceString, int sentenceID, bool boundaryRules)
	{
		if (!m_options.sourceSyntax) {
			return SentenceAlignment::processSourceSentence(sourceString, sentenceID, boundaryRules);
		}

		string sourceStringCPP(sourceString);
		try {
			ProcessAndStripXMLTags(sourceStringCPP, sourceTree,
				m_sourceLabelCollection ,
				m_sourceTopLabelCollection,
				false);
		} catch (const XmlException & e) {
			std::cerr << "WARNING: failed to process source sentence at line "
				<< sentenceID << ": " << e.getMsg() << std::endl;
			return false;
		}
		source = tokenize(sourceStringCPP.c_str());
		return true;
	}
