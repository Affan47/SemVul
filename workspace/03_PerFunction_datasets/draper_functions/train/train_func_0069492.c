Java_magick_MagickImage_setImageProfile
		(JNIEnv *env, jobject self, jstring profileName, jbyteArray profileData)
	{
			Image *image = NULL;
			const char *cstrProfileName;
			unsigned char *cProfileData;
			size_t cProfileSize;
			unsigned int retVal;

			image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
			if (image == NULL) {
		throwMagickException(env, "No image to set file name");
		return JNI_FALSE;
			}

			if (profileName == NULL) {
					cstrProfileName = NULL;
			}
			else {
					cstrProfileName = (*env)->GetStringUTFChars(env, profileName, 0);
			}

			if (profileData == NULL) {
					cProfileData = NULL;
					cProfileSize = 0;
			}
			else {
					cProfileSize = (*env)->GetArrayLength(env, profileData);
					cProfileData = (*env)->GetByteArrayElements(env, profileData, 0);
			}


      if (cProfileData == NULL) {
				retVal = DeleteImageProfile(image,cstrProfileName);
      } else {
					StringInfo * profile_info = NULL;
					profile_info = AcquireStringInfo(cProfileSize);
					SetStringInfoDatum(profile_info, cProfileData);

					retVal =
							SetImageProfile(image, cstrProfileName, profile_info);

					profile_info = DestroyStringInfo(profile_info);
				}

			if (profileData != NULL) {
					(*env)->ReleaseByteArrayElements(env, profileData, cProfileData, 0);
			}

			if (profileName != NULL) {
					(*env)->ReleaseStringUTFChars(env, profileName, cstrProfileName);
			}

			return (retVal ? JNI_TRUE : JNI_FALSE);
	}
