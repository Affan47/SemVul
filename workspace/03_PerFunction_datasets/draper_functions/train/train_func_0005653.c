I2C_read_ack(I2C_TypeDef* I2Cx) {
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
	while( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) );
	uint8_t data = I2C_ReceiveData(I2Cx);
	return data;
}
