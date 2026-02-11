stun_attr2str(int msg)
{
	switch (msg) {
	case STUN_MAPPED_ADDRESS:
		return "Mapped Address";
	case STUN_RESPONSE_ADDRESS:
		return "Response Address";
	case STUN_CHANGE_REQUEST:
		return "Change Request";
	case STUN_SOURCE_ADDRESS:
		return "Source Address";
	case STUN_CHANGED_ADDRESS:
		return "Changed Address";
	case STUN_USERNAME:
		return "Username";
	case STUN_PASSWORD:
		return "Password";
	case STUN_MESSAGE_INTEGRITY:
		return "Message Integrity";
	case STUN_ERROR_CODE:
		return "Error Code";
	case STUN_UNKNOWN_ATTRIBUTES:
		return "Unknown Attributes";
	case STUN_REFLECTED_FROM:
		return "Reflected From";
	}
	return "Non-RFC3489 Attribute";
}
