HandleCharacterScreen(void)
{

	if (!GameConfig.CharacterScreen_Visible)
		return;

	if (Me.points_to_distribute > 0) {
		if (MouseCursorIsOnButton(MORE_STR_BUTTON, GetMousePos_x(), GetMousePos_y()) && MouseLeftClicked()) {
			Me.base_strength++;
			Me.points_to_distribute--;
		}
		if (MouseCursorIsOnButton(MORE_DEX_BUTTON, GetMousePos_x(), GetMousePos_y()) && MouseLeftClicked()) {
			Me.base_dexterity++;
			Me.points_to_distribute--;
		}
		if (MouseCursorIsOnButton(MORE_MAG_BUTTON, GetMousePos_x(), GetMousePos_y()) && MouseLeftClicked()) {
			Me.base_cooling++;
			Me.points_to_distribute--;
		}
		if (MouseCursorIsOnButton(MORE_VIT_BUTTON, GetMousePos_x(), GetMousePos_y()) && MouseLeftClicked()) {
			Me.base_physique++;
			Me.points_to_distribute--;
		}

	}

}
