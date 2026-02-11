setPickAppearance(bool pick) {
    m_pick = pick;
	setBrush(pick ? PickColor : NormalColor);
}
