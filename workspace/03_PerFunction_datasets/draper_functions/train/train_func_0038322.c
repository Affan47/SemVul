GetVariable (DBObjRecord *record,DBCoordinate coord)
		{
		switch ((GridIF->Data ())->Type ())
			{
			case DBTypeGridContinuous:
				{
				DBFloat value;
				if (GridIF->Value (LayerRec,coord,&value))
						TargetFLD->Float (record,value);
				else	TargetFLD->Float (record,TargetFLD->FloatNoData ());
				} break;
			case DBTypeGridDiscrete:
				{
				DBObjRecord *grdRec;
				if ((grdRec = GridIF->GridItem (LayerRec,coord)) != (DBObjRecord *) NULL)
					switch (SourceFLD->Type ())
						{
						case DBVariableString:
							TargetFLD->String (record,SourceFLD->String (grdRec));	break;
						case DBVariableInt:
							TargetFLD->Int (record,SourceFLD->Int (grdRec));			break;
						case DBVariableFloat:
							TargetFLD->Float (record,SourceFLD->Float (grdRec));		break;
						default:	break;
						}
				else
					switch (SourceFLD->Type ())
						{
						case DBVariableString:
							TargetFLD->String (record,"");									break;
						case DBVariableInt:
							TargetFLD->Int (record,SourceFLD->IntNoData ());			break;
						case DBVariableFloat:
							TargetFLD->Float (record,SourceFLD->FloatNoData ());		break;
						default:	break;
						}
				} break;
			default:
				CMmsgPrint (CMmsgUsrError,"Invalid grid type in: CMDgrdVariable:GetVariable ()");
				break;
			}
		}
