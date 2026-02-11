params() const
{
	if (haveMultiParSelection()) {


		static ParagraphParameters empty;
		return empty;
	}
	return bufferview()->cursor().innerParagraph().params();
}
