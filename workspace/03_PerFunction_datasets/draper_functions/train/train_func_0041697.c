println(int n, ostream& fout)
{
	list<Klass* >::iterator k;

	tab(n,fout); fout << "class " << fKlassName << " {";

	tab(n,fout); fout << "  private:";
		tab(n+1,fout); fout << "int \tfSamplingFreq;";

		for (k = fSubClassList.begin(); k != fSubClassList.end(); k++) 	(*k)->println(n+1, fout);

		printlines(n+1, fDeclCode, fout);

	tab(n,fout); fout << "  public:";

		tab(n+1,fout); fout 	<< "int getNumInputs() \t{ "
						<< "return " << fNumInputs << "; }";
		tab(n+1,fout); fout 	<< "int getNumOutputs() \t{ "
						<< "return " << fNumOutputs << "; }";

		tab(n+1,fout); fout << "void init(int samplingFreq) {";
			tab(n+2,fout); fout << "fSamplingFreq = samplingFreq;";
			printlines(n+2, fInitCode, fout);
		tab(n+1,fout); fout << "}";

		tab(n+1,fout); fout << subst("void fill (int count, $0 output[]) {", ifloat());
            printlines (n+2, fZone1Code, fout);
            printlines (n+2, fZone2Code, fout);
            printlines (n+2, fZone2bCode, fout);
            printlines (n+2, fZone3Code, fout);
            printLoopGraphInternal(n+2,fout);
 		tab(n+1,fout); fout << "}";

	tab(n,fout); fout << "};\n" << endl;
}
