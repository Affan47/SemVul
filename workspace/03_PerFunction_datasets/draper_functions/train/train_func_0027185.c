bin_ulongvec(struct file *file,
	void __user *oldval, size_t oldlen, void __user *newval, size_t newlen)
{
	ssize_t copied = 0;
	char *buffer;
	ssize_t result;

	result = -ENOMEM;
	buffer = kmalloc(BUFSZ, GFP_KERNEL);
	if (!buffer)
		goto out;

	if (oldval && oldlen) {
		unsigned long __user *vec = oldval;
		size_t length = oldlen / sizeof(*vec);
		char *str, *end;
		int i;

		result = kernel_read(file, 0, buffer, BUFSZ - 1);
		if (result < 0)
			goto out_kfree;

		str = buffer;
		end = str + result;
		*end++ = '\0';
		for (i = 0; i < length; i++) {
			unsigned long value;

			value = simple_strtoul(str, &str, 10);
			while (isspace(*str))
				str++;

			result = -EFAULT;
			if (put_user(value, vec + i))
				goto out_kfree;

			copied += sizeof(*vec);
			if (!isdigit(*str))
				break;
		}
	}

	if (newval && newlen) {
		unsigned long __user *vec = newval;
		size_t length = newlen / sizeof(*vec);
		char *str, *end;
		int i;

		str = buffer;
		end = str + BUFSZ;
		for (i = 0; i < length; i++) {
			unsigned long value;

			result = -EFAULT;
			if (get_user(value, vec + i))
				goto out_kfree;

			str += scnprintf(str, end - str, "%lu\t", value);
		}

		result = kernel_write(file, buffer, str - buffer, 0);
		if (result < 0)
			goto out_kfree;
	}
	result = copied;
out_kfree:
	kfree(buffer);
out:
	return result;
}
