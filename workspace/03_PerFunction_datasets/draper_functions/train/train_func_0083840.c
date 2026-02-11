usb_exchange(struct gspca_dev *gspca_dev,
			const struct usb_action *action)
{
	while (action->req) {
		switch (action->req) {
		case 0xa0:
			reg_w(gspca_dev, action->val, action->idx);
			break;
		case 0xa1:
			reg_r(gspca_dev, action->idx);
			break;
		case 0xaa:
			i2c_write(gspca_dev,
				  action->val,
				  action->idx & 0xff,
				  action->idx >> 8);
			break;
		case 0xbb:
			i2c_write(gspca_dev,
				  action->idx >> 8,
				  action->idx & 0xff,
				  action->val);
			break;
		default:

			msleep(action->idx);
			break;
		}
		action++;
		msleep(1);
	}
}
