move( char direction, int speed )
{
	switch(direction)
	{
		case 'f':
			return send_cmd_action(1,speed);
		case 'b':
			return send_cmd_action(2,speed);
		case 'l':
			return send_cmd_action(3,speed);
		case 'r':
			return send_cmd_action(4,speed);
		default:
			cout << "Error in parameter of move()";
			return false;
	}
}
