processCommand(int command, QPointF pt)
{

	switch(command)
	{
		case QGLE::StartNewLineWithPoint:
			createNewLine(pt);
			break;

		case QGLE::SetLineEndPoint:
			setLineEndPoint(pt);
			break;

		case QGLE::EndNewLine:
			completeNewLine();
			break;

		case QGLE::StartNewTanLineWithPoint:
			createNewTanLine(pt);
			break;

		case QGLE::EndNewTanLine:
			completeNewTanLine();
			break;

		case QGLE::SetTanLineEndPoint:
			setTanLineEndPoint(pt);
			break;

		case QGLE::StartNewPerpLineWithPoint:
			createNewPerpLine(pt);
			break;

		case QGLE::EndNewPerpLine:
			completeNewPerpLine();
			break;

		case QGLE::SetPerpLineEndPoint:
			setPerpLineEndPoint(pt);
			break;

		case QGLE::StartNewCircleWithCentre:
			createNewCircle(pt);
			break;

		case QGLE::SetCircleEdgePoint:
			setCircleEdgePoint(pt);
			break;

		case QGLE::EndNewCircle:
			completeNewCircle();
			break;

		case QGLE::StartNewEllipseWithCorner:
			createNewEllipse(pt);
			break;

		case QGLE::SetEllipseSecondCorner:
			setEllipseSecondCorner(pt);
			break;

		case QGLE::EndNewEllipse:
			completeNewEllipse();
			break;


		case QGLE::StartNewArcWithPoint:
			createNewArc(pt);
			break;

		case QGLE::SetArcEndPoint:
			setArcEndPoint(pt);
			break;

		case QGLE::SetArcMidPoint:
			setArcMidPoint(pt);
			break;

		case QGLE::EndNewArc:
			completeNewArc();
			break;

		case QGLE::SetAMove:
			setAmove(pt);
			break;

		case QGLE::Cancel:
			cancelCommand();
			break;

		case QGLE::CreateTextObject:
			createNewTextObject(pt);
			break;

		case QGLE::DeleteSelected:
			deleteSelectedObjects();
			break;


	}
}
