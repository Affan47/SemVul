setModelIndexFromMultiplied(long multiplied) {
	if (m_indexSynched) {


		if (m_index != multiplied / ModelPart::indexMultiplier) {

		}

		return;
	}

	m_indexSynched = true;
	setModelIndex(multiplied / ModelPart::indexMultiplier);
}
