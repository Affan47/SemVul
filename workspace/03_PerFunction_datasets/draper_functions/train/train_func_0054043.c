addPartToBin(ModelPart *modelPart, int position) {
	PartsBinPaletteWidget *bin = m_currentBin? m_currentBin: getOrOpenMyPartsBin();
	addPartToBinAux(bin,modelPart,position);
}
