igb_reg_test(struct igb_adapter *adapter, u64 *data)
{
	struct e1000_hw *hw = &adapter->hw;
	struct igb_reg_test *test;
	u32 value, before, after;
	u32 i, toggle;

	switch (adapter->hw.mac.type) {
	case e1000_i350:
	case e1000_i354:
		test = reg_test_i350;
		toggle = 0x7FEFF3FF;
		break;
	case e1000_i210:
	case e1000_i211:
		test = reg_test_i210;
		toggle = 0x7FEFF3FF;
		break;
	case e1000_82580:
		test = reg_test_82580;
		toggle = 0x7FEFF3FF;
		break;
	case e1000_82576:
		test = reg_test_82576;
		toggle = 0x7FFFF3FF;
		break;
	default:
		test = reg_test_82575;
		toggle = 0x7FFFF3FF;
		break;
	}


	before = rd32(E1000_STATUS);
	value = (rd32(E1000_STATUS) & toggle);
	wr32(E1000_STATUS, toggle);
	after = rd32(E1000_STATUS) & toggle;
	if (value != after) {
		dev_err(&adapter->pdev->dev,
			"failed STATUS register test got: 0x%08X expected: 0x%08X\n",
			after, value);
		*data = 1;
		return 1;
	}

	wr32(E1000_STATUS, before);


	while (test->reg) {
		for (i = 0; i < test->array_len; i++) {
			switch (test->test_type) {
			case PATTERN_TEST:
				REG_PATTERN_TEST(test->reg +
						(i * test->reg_offset),
						test->mask,
						test->write);
				break;
			case SET_READ_TEST:
				REG_SET_AND_CHECK(test->reg +
						(i * test->reg_offset),
						test->mask,
						test->write);
				break;
			case WRITE_NO_TEST:
				writel(test->write,
				    (adapter->hw.hw_addr + test->reg)
					+ (i * test->reg_offset));
				break;
			case TABLE32_TEST:
				REG_PATTERN_TEST(test->reg + (i * 4),
						test->mask,
						test->write);
				break;
			case TABLE64_TEST_LO:
				REG_PATTERN_TEST(test->reg + (i * 8),
						test->mask,
						test->write);
				break;
			case TABLE64_TEST_HI:
				REG_PATTERN_TEST((test->reg + 4) + (i * 8),
						test->mask,
						test->write);
				break;
			}
		}
		test++;
	}

	*data = 0;
	return 0;
}
