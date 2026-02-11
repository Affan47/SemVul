Pk11Install_File_Cleanup(Pk11Install_File* _this)
{
	if(_this->jarPath) {
		PR_Free(_this->jarPath);
		_this->jarPath = NULL;
	}
	if(_this->relativePath) {
		PR_Free(_this->relativePath);
		_this->relativePath = NULL;
	}
	if(_this->absolutePath) {
		PR_Free(_this->absolutePath);
		_this->absolutePath = NULL;
	}

	_this->permissions = 0;
	_this->executable = PR_FALSE;
}
