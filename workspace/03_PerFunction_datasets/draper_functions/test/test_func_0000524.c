I2C_IRQHandler(void)
{
	uint8_t StatValue;


	StatValue = I2C_I2CSTAT;
	switch ( StatValue )
	{
	case 0x08:


		WrIndex = 0;
		I2C_I2CDAT = I2CMasterBuffer[WrIndex++];
		I2C_I2CCONCLR = (I2CONCLR_SIC | I2CONCLR_STAC);
		I2CMasterState = I2CSTATE_PENDING;
		break;

	case 0x10:


		RdIndex = 0;

		I2C_I2CDAT = I2CMasterBuffer[WrIndex++];
		I2C_I2CCONCLR = (I2CONCLR_SIC | I2CONCLR_STAC);
	break;

	case 0x18:


		I2C_I2CDAT = I2CMasterBuffer[WrIndex++];
		I2C_I2CCONCLR = I2CONCLR_SIC;
		break;

	case 0x20:


		I2C_I2CCONSET = I2CONSET_STO;
		I2C_I2CCONCLR = I2CONCLR_SIC;
		I2CMasterState = I2CSTATE_SLA_NACK;
		break;

	case 0x28:


		if ( WrIndex < I2CWriteLength )
		{

			I2C_I2CDAT = I2CMasterBuffer[WrIndex++];
		}
		else
		{
			if ( I2CReadLength != 0 )
			{


				I2C_I2CCONSET = I2CONSET_STA;
			}
			else
			{
				I2CMasterState = I2CSTATE_ACK;
				I2C_I2CCONSET = I2CONSET_STO;
			}
		}
		I2C_I2CCONCLR = I2CONCLR_SIC;
		break;

	case 0x30:


		I2C_I2CCONSET = I2CONSET_STO;
		I2C_I2CCONCLR = I2CONCLR_SIC;
		I2CMasterState = I2CSTATE_NACK;
		break;

	case 0x38:


		I2CMasterState = I2CSTATE_ARB_LOSS;
		I2C_I2CCONCLR = I2CONCLR_SIC;
		break;

	case 0x40:


		if ( I2CReadLength == 1 )
		{

			I2C_I2CCONCLR = I2CONCLR_AAC;
		}
		else
		{

			I2C_I2CCONSET = I2CONSET_AA;
		}
		I2C_I2CCONCLR = I2CONCLR_SIC;
		break;

	case 0x48:


		I2C_I2CCONSET = I2CONSET_STO;
		I2C_I2CCONCLR = I2CONCLR_SIC;
		I2CMasterState = I2CSTATE_SLA_NACK;
		break;

	case 0x50:


		I2CSlaveBuffer[RdIndex++] = I2C_I2CDAT;
		if ( RdIndex < (I2CReadLength-1) )
		{

			I2C_I2CCONSET = I2CONSET_AA;
		}
		else
		{

			I2C_I2CCONCLR = I2CONCLR_AAC;
		}
		I2C_I2CCONCLR = I2CONCLR_SIC;
		break;

	case 0x58:


		I2CSlaveBuffer[RdIndex++] = I2C_I2CDAT;
		I2CMasterState = I2CSTATE_ACK;
		I2C_I2CCONSET = I2CONSET_STO;
		I2C_I2CCONCLR = I2CONCLR_SIC;
		break;


	default:
		I2C_I2CCONCLR = I2CONCLR_SIC;
	break;
  }
  return;
}
