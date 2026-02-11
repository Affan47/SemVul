elementId(const KBBScalableGraphicWidget::itemType itemType)
{
	QString eId;

	switch (itemType) {
		case KBBScalableGraphicWidget::background:
			eId = "background";
			break;
		case KBBScalableGraphicWidget::blackbox:
			eId = "blackbox";
			break;
		case KBBScalableGraphicWidget::blackboxGrid:
			eId = "blackbox_grid";
			break;
		case KBBScalableGraphicWidget::cursor:
			eId = "cursor";
			break;
		case KBBScalableGraphicWidget::informationBackground:
			eId = "information_background";
			break;
		case KBBScalableGraphicWidget::interactionInfoDeflection:
			eId = "interaction_info_deflection";
			break;
		case KBBScalableGraphicWidget::interactionInfoHit:
			eId = "interaction_info_hit";
			break;
		case KBBScalableGraphicWidget::interactionInfoNothing:
			eId = "interaction_info_nothing";
			break;
		case KBBScalableGraphicWidget::interactionInfoReflection:
			eId = "interaction_info_reflection";
			break;
		case KBBScalableGraphicWidget::interactionInfoReflectionSym:
			eId = "interaction_info_reflection_sym";
			break;
		case KBBScalableGraphicWidget::laser0:
			eId = "laser_0";
			break;
		case KBBScalableGraphicWidget::laser90:
			eId = "laser_90";
			break;
		case KBBScalableGraphicWidget::laser180:
			eId = "laser_180";
			break;
		case KBBScalableGraphicWidget::laser270:
			eId = "laser_270";
			break;
		case KBBScalableGraphicWidget::markerNothing:
			eId = "marker_nothing";
			break;
		case KBBScalableGraphicWidget::playerBall:
			eId = "player_ball";
			break;
		case KBBScalableGraphicWidget::playerRay:
			eId = "player_ray";
			break;
		case KBBScalableGraphicWidget::resultBackground:
			eId = "result_background";
			break;
		case KBBScalableGraphicWidget::resultBackgroundHighlight:
			eId = "result_background_highlight";
			break;
		case KBBScalableGraphicWidget::resultHit:
			eId = "result_hit";
			break;
		case KBBScalableGraphicWidget::resultReflection:
			eId = "result_reflection";
			break;
		case KBBScalableGraphicWidget::rightPlayerBall:
			eId = "right_player_ball";
			break;
		case KBBScalableGraphicWidget::solutionBall:
			eId = "solution_ball";
			break;
		case KBBScalableGraphicWidget::solutionRay:
			eId = "solution_ray";
			break;
		case KBBScalableGraphicWidget::tutorialMarker:
			eId = "tutorial_marker";
			break;
		case KBBScalableGraphicWidget::unsureBall:
			eId = "unsure_ball";
			break;
		case KBBScalableGraphicWidget::wrongPlayerBall:
			eId = "wrong_player_ball";
			break;
		default:
			eId = "none";
			break;
	}

	return eId;
}
