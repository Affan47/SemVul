sendNumber(
	FLMUINT			uiTag,
	FLMUINT64		ui64Value,
	FLMINT64			i64Value)
{
	RCODE				rc = FERR_OK;


	switch( uiTag)
	{
		case WIRE_VALUE_AREA_ID:
		case WIRE_VALUE_OP_SEQ_NUM:
		case WIRE_VALUE_FLAGS:
		case WIRE_VALUE_CLIENT_VERSION:
		case WIRE_VALUE_SESSION_ID:
		case WIRE_VALUE_SESSION_COOKIE:
		case WIRE_VALUE_CONTAINER_ID:
		case WIRE_VALUE_INDEX_ID:
		case WIRE_VALUE_ITEM_ID:
		case WIRE_VALUE_TRANSACTION_ID:
		case WIRE_VALUE_TRANSACTION_TYPE:
		case WIRE_VALUE_DRN:
		case WIRE_VALUE_COUNT:
		case WIRE_VALUE_AUTOTRANS:
		case WIRE_VALUE_MAX_LOCK_WAIT:
		case WIRE_VALUE_RECORD_COUNT:
		case WIRE_VALUE_BOOLEAN:
		case WIRE_VALUE_ITERATOR_ID:
		case WIRE_VALUE_SHARED_DICT_ID:
		case WIRE_VALUE_PARENT_DICT_ID:
		case WIRE_VALUE_TYPE:
		case WIRE_VALUE_NUMBER1:
		case WIRE_VALUE_NUMBER2:
		case WIRE_VALUE_NUMBER3:
		case WIRE_VALUE_ADDRESS:
		case WIRE_VALUE_FLAIM_VERSION:
		{
			if( RC_BAD( rc = writeUnsignedNumber( uiTag, ui64Value)))
			{
				goto Exit;
			}
			break;
		}

		case WIRE_VALUE_SIGNED_NUMBER:
		{
			if( RC_BAD( rc = writeSignedNumber( uiTag, i64Value)))
			{
				goto Exit;
			}
			break;
		}

		default:
		{
#ifdef FLM_DEBUG
			flmAssert( 0);
#else
			rc = RC_SET( FERR_NOT_IMPLEMENTED);
			goto Exit;
#endif
		}
	}

Exit:

	return( rc);
}
