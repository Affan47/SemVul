putNWChemMP2KeywordsInfoInTextEditor()
{
	if(strstr(selectedMethod,"MP2"))
	{
       		gabedit_text_insert (GABEDIT_TEXT(text), NULL, &nwchemColorFore.keyWord, &nwchemColorBack.keyWord, "mp2\n", -1);
        	gabedit_text_insert (GABEDIT_TEXT(text), NULL, NULL, NULL, " freeze core atomic\n",-1);
        	gabedit_text_insert (GABEDIT_TEXT(text), NULL, NULL, NULL, "# freeze virtual 5\n",-1);
        	gabedit_text_insert (GABEDIT_TEXT(text), NULL, NULL, NULL, "# tight\n",-1);
        	gabedit_text_insert (GABEDIT_TEXT(text), NULL, NULL, NULL, "# print\n",-1);
        	gabedit_text_insert (GABEDIT_TEXT(text), NULL, NULL, NULL, "# noprint\n",-1);
        	gabedit_text_insert (GABEDIT_TEXT(text), NULL, NULL, NULL, "# riapprox V\n",-1);
        	gabedit_text_insert (GABEDIT_TEXT(text), NULL, NULL, NULL, "# riapprox SVS\n",-1);
       		gabedit_text_insert (GABEDIT_TEXT(text), NULL, &nwchemColorFore.keyWord, &nwchemColorBack.keyWord, "end\n", -1);
	}
}
