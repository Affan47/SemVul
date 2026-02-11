model_format_end (PRN *prn)
{
    if (tex_format(prn)) {
	pputs(prn, "\n\\end{center}\n");
	if (tex_doc_format(prn)) {
	    pputs(prn, "\n\\end{document}\n");
	}
    } else if (rtf_doc_format(prn)) {
	pputs(prn, "\n}\n");
    }
}
