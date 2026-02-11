localScale(glm::vec3 & s) {

	glm::mat4 transformation = glm::inverse(modelMatrix) * glm::mat4();
	transformation = glm::scale(glm::mat4(), s) * transformation;
	transformation = modelMatrix * transformation;


	position = glm::vec3(transformation * glm::vec4(position, 1));


	transformation = glm::inverse(vecModelMatrix) * glm::mat4();
	transformation = glm::scale(glm::mat4(), s) * transformation;
	transformation = vecModelMatrix * transformation;


	direction = glm::vec3(transformation * glm::vec4(direction, 1));
	up = glm::vec3(transformation * glm::vec4(up, 1));


	updateMatrices();
}
