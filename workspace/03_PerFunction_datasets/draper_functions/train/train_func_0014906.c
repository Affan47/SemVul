i2400m_roq_log_entry_print(struct i2400m *i2400m, unsigned index,
				unsigned e_index,
				struct i2400m_roq_log_entry *e)
{
	struct device *dev = i2400m_dev(i2400m);

	switch(e->type) {
	case I2400M_RO_TYPE_RESET:
		dev_err(dev, "q#%d reset           ws %u cnt %u sn %u/%u"
			" - new nws %u\n",
			index, e->ws, e->count, e->sn, e->nsn, e->new_ws);
		break;
	case I2400M_RO_TYPE_PACKET:
		dev_err(dev, "q#%d queue           ws %u cnt %u sn %u/%u\n",
			index, e->ws, e->count, e->sn, e->nsn);
		break;
	case I2400M_RO_TYPE_WS:
		dev_err(dev, "q#%d update_ws       ws %u cnt %u sn %u/%u"
			" - new nws %u\n",
			index, e->ws, e->count, e->sn, e->nsn, e->new_ws);
		break;
	case I2400M_RO_TYPE_PACKET_WS:
		dev_err(dev, "q#%d queue_update_ws ws %u cnt %u sn %u/%u"
			" - new nws %u\n",
			index, e->ws, e->count, e->sn, e->nsn, e->new_ws);
		break;
	default:
		dev_err(dev, "q#%d BUG? entry %u - unknown type %u\n",
			index, e_index, e->type);
		break;
	}
}
