GetCML ()
{
	if (m_CML.length () == 0) {
		GsfOutput *output = gsf_output_memory_new ();
		GetDocument ()->GetApp ()->Save (output, "chemical/x-cml", this, m_Content);
		size_t l = gsf_output_size (output);
		if (l > 0)
			m_CML.assign (reinterpret_cast <char const *> (gsf_output_memory_get_bytes (GSF_OUTPUT_MEMORY (output))), l);
		g_object_unref (output);
	}
	return m_CML;
}
