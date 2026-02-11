setBorderWalls(bool showing)
{
	foreach (Kolf::Wall* wall, borderWalls)
		wall->setVisible(showing);
}
