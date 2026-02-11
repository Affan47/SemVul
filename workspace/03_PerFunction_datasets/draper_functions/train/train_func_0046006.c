load()
{
	QSettings settings( "Attal", "attal-client" );

	_fightSettings.isAnimationEnabled = settings.value( "FightSettings/isAnimationEnabled", true ).toBool();
	_fightSettings.areCellsVisible = settings.value( "FightSettings/areCellsVisible", true ).toBool();
	_fightSettings.animationSpeed = settings.value( "FightSettings/animationSpeed", 7 ).toInt();

	_strategyModeSettings.isAnimationEnabled = settings.value( "StrategyModeSettings/isAnimationEnabled", true ).toBool();
	_strategyModeSettings.isMapVisible = settings.value( "StrategyModeSettings/isMapVisible", true ).toBool();
	_strategyModeSettings.isSoundOn = settings.value( "StrategyModeSettings/isSoundOn", true ).toBool();
	_strategyModeSettings.isMusicOn = settings.value( "StrategyModeSettings/isMusicOn", true ).toBool();
	_strategyModeSettings.connectionName = settings.value( "StrategyModeSettings/connectionName", "New Player" ).toString();

	_mode = (DispositionMode) settings.value( "Display/dispositionMode", (int) DM_FULL ).toInt();
}
