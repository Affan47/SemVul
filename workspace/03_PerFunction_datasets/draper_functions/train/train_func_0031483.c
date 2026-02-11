TickCallback (guint aTime,
			   guint aDuration,
			   char *aState)
{
	guint i;

	DD ("Tick signal received, aState %s, aTime %d, aDuration %d", aState, aTime, aDuration);

	for (i = 0; i < TOTEM_STATE_INVALID; i++) {
		if (strcmp (aState, totem_states[i]) == 0) {
			this->mState = (TotemStates) i;
			break;
		}
	}

	this->mTime = aTime;
	this->mDuration = aDuration;

#ifdef TOTEM_GMP_PLUGIN
        if (!this->mNPObjects[ePluginScriptable].IsNull ()) {
                NPObject *object = this->mNPObjects[ePluginScriptable];
                totemGMPPlayer *scriptable = static_cast<totemGMPPlayer*>(object);
                switch (this->mState) {
		case TOTEM_STATE_PLAYING:
			scriptable->mPluginState = totemGMPPlayer::eState_Playing;
			break;
		case TOTEM_STATE_PAUSED:
			scriptable->mPluginState = totemGMPPlayer::eState_Paused;
			break;
		case TOTEM_STATE_STOPPED:
			scriptable->mPluginState = totemGMPPlayer::eState_Stopped;
			break;
		default:
			scriptable->mPluginState = totemGMPPlayer::eState_Undefined;
		}
	}
#endif

#ifdef TOTEM_NARROWSPACE_PLUGIN
        if (!this->mNPObjects[ePluginScriptable].IsNull ()) {
                NPObject *object = this->mNPObjects[ePluginScriptable];
                totemNarrowSpacePlayer *scriptable = static_cast<totemNarrowSpacePlayer*>(object);
                switch (this->mState) {
		case TOTEM_STATE_PLAYING:
		case TOTEM_STATE_PAUSED:
			scriptable->mPluginState = totemNarrowSpacePlayer::eState_Playable;
			break;
		case TOTEM_STATE_STOPPED:
			if (scriptable->mPluginState == totemNarrowSpacePlayer::eState_Playable) {
				scriptable->mPluginState = totemNarrowSpacePlayer::eState_Complete;


				this->mTime = this->mDuration;
			} else
				scriptable->mPluginState = totemNarrowSpacePlayer::eState_Waiting;
			break;
		default:
			scriptable->mPluginState = totemNarrowSpacePlayer::eState_Waiting;
		}
	}
#endif
}
