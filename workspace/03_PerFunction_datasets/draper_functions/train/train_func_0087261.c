tool_link_event(void *ctx)
{
	struct tool_ctx *tc = ctx;
	enum ntb_speed speed;
	enum ntb_width width;
	int up;

	up = ntb_link_is_up(tc->ntb, &speed, &width);

	dev_dbg(&tc->ntb->dev, "link is %s speed %d width %d\n",
		up ? "up" : "down", speed, width);
}
